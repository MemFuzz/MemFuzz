//========================================================================
//
// pdfinfo.cc
//
// Copyright 1998-2013 Glyph & Cog, LLC
//
//========================================================================
/*Modification Begin*/
#include <signal.h>
#include <fstream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <dirent.h>
/*Modification End*/
#include <aconf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include "gmem.h"
#include "gmempp.h"
#include "parseargs.h"
#include "GString.h"
#include "gfile.h"
#include "GlobalParams.h"
#include "Object.h"
#include "Stream.h"
#include "Array.h"
#include "Dict.h"
#include "XRef.h"
#include "Catalog.h"
#include "Page.h"
#include "PDFDoc.h"
#include "CharTypes.h"
#include "UnicodeMap.h"
#include "TextString.h"
#include "UTF8.h"
#include "Zoox.h"
#include "Error.h"
#include "config.h"
#include "fuzz_config.h"
static void printInfoString(Object *infoDict, const char *infoKey,
			    ZxDoc *xmp, const char *xmpKey1,
			    const char *xmpKey2,
			    const char *text, GBool parseDate,
			    UnicodeMap *uMap);
static GString *parseInfoDate(GString *s);
static GString *parseXMPDate(GString *s);
static void printBox(const char *text, PDFRectangle *box);

static int firstPage = 1;
static int lastPage = 0;
static GBool printBoxes = gFalse;
static GBool printMetadata = gFalse;
static GBool rawDates = gFalse;
static char textEncName[128] = "";
static char ownerPassword[33] = "\001";
static char userPassword[33] = "\001";
static char cfgFileName[256] = "";
static GBool printVersion = gFalse;
static GBool printHelp = gFalse;

static ArgDesc argDesc[] = {
  {"-f",      argInt,      &firstPage,        0,
   "first page to convert"},
  {"-l",      argInt,      &lastPage,         0,
   "last page to convert"},
  {"-box",    argFlag,     &printBoxes,       0,
   "print the page bounding boxes"},
  {"-meta",   argFlag,     &printMetadata,    0,
   "print the document metadata (XML)"},
  {"-rawdates", argFlag,   &rawDates,         0,
   "print the undecoded date strings directly from the PDF file"},
  {"-enc",    argString,   textEncName,    sizeof(textEncName),
   "output text encoding name"},
  {"-opw",    argString,   ownerPassword,  sizeof(ownerPassword),
   "owner password (for encrypted files)"},
  {"-upw",    argString,   userPassword,   sizeof(userPassword),
   "user password (for encrypted files)"},
  {"-cfg",        argString,      cfgFileName,    sizeof(cfgFileName),
   "configuration file to use in place of .xpdfrc"},
  {"-v",      argFlag,     &printVersion,  0,
   "print copyright and version info"},
  {"-h",      argFlag,     &printHelp,     0,
   "print usage information"},
  {"-help",   argFlag,     &printHelp,     0,
   "print usage information"},
  {"--help",  argFlag,     &printHelp,     0,
   "print usage information"},
  {"-?",      argFlag,     &printHelp,     0,
   "print usage information"},
  {NULL}
};

/*Modification Begin*/
//It is declared in Parser.cc
extern ObjectPool objPool;
std::string err_msg = "no error";
extern unsigned char* a_file;
void setup_shm(void) {

  char* shm_str = getenv(SHM_ENV_VAR_GENERATOR);
  if(shm_str == NULL)
  {
      err_msg = "No shm set";
      exit(1);
  }
  int shm_id = std::stoi(shm_str);
  //shm_id = shmget(3333, FILE_LENGTH_MAX, 0600);

  if (shm_id < 0)
  {
      err_msg = std::string("shmget() failed, shmid is ") + std::string(shm_str) + ", errno is ";
      switch(errno)
      {
          case EACCES:
              err_msg += "EACCES";
              break;
          case EEXIST:
              err_msg += "EEXIST";
              break;
          case EINVAL:
              err_msg += "EINVAL";
              break;
          case ENFILE:
              err_msg += "ENFILE";
              break;
          case ENOENT:
              err_msg += "ENOENT";
              break;
          case ENOMEM:
              err_msg += "ENOMEM";
              break;
          case ENOSPC:
              err_msg += "ENOSPC";
              break;
          case EPERM:
              err_msg += "EPERM";
              break;
          default:
              err_msg += "UNKNOWN";
      }
      exit(1);
  }

  a_file = (unsigned char*)shmat(shm_id, NULL, 0);
  
  if (!a_file)
  {
      err_msg = "shmat() failed";
      exit(1);
  }

}

void mem_usage(double& vm_usage, double& resident_set) 
{
    vm_usage = 0.0;
    resident_set = 0.0;
    std::ifstream stat_stream("/proc/self/stat", std::ios_base::in);
    std::string pid, comm, state, ppid, pgrp, session, tty_nr;
    std::string tpgid, flags, minflt, cminflt, majflt, cmajflt;
    std::string utime, stime, cutime, cstime, priority, nice;
    std::string O, itrealvalue, starttime;
    unsigned long vsize;
    long rss;
    stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr
                >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt
                >> utime >> stime >> cutime >> cstime >> priority >> nice
                >> O >> itrealvalue >> starttime >> vsize >> rss;
    stat_stream.close();
    long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024;
    vm_usage = vsize / 1024.0;
    resident_set = rss * page_size_kb;
}

void dump_err()
{
    FILE* fp = fopen("/tmp/err", "w");
    fprintf(fp, "%s\n", err_msg.c_str());
    fclose(fp);
}

//send a file to AFL, if len == 0, no more files to send
//send and receive files via shared memory
static void send_file(unsigned len, const unsigned char* buf)
{
    if(len > FILE_LENGTH_MAX)
    {
        write(GEN_ST_FD, &len, 4);
        return ;
    }
    memcpy(a_file, buf, len);
    write(GEN_ST_FD, &len, 4);
}

static void receive_file(unsigned *len, unsigned char* buf)
{
    if(read(GEN_CTL_FD, len, 4) != 4)
    {
        err_msg = "read error in receive_file()\n";
        exit(1);
    }
    if(*len >= FILE_LENGTH_MAX)
    {
        return ;
    }
    memcpy(buf, a_file, *len);
}
/*Send and receive files via pipe
void send_file(unsigned len, const unsigned char* buf)
{ 
    unsigned len1 = len, wt = 0;
    write(GEN_ST_FD, &len, 4);
	if(len >= FILE_LENGTH_MAX)
		return ;
    while(len1 > 65535)
    {
      wt += write(GEN_ST_FD, buf + wt, 65535);
      len1 = len - wt;
    }
    
    if(len1 != 0)
    {
        wt += write(GEN_ST_FD, buf + wt, len1);
    }
}

//receive a file from AFL
void receive_file(unsigned *len, unsigned char* buf)
{
	unsigned rd = 0;
    unsigned len1;
    if(read(GEN_CTL_FD, len, 4) != 4) 
    {
        err_msg = "read error in receive_file()\n";
        exit(1);
    }
    len1 = *len;
	if(len1 >= FILE_LENGTH_MAX)
	{
		*len = -1;
		return ;
	}
    while(len1 > 65535)
    {
        rd += read(GEN_CTL_FD, buf + rd, 65535);
        len1 = *len - rd;
    }
    if(len1 != 0)
        rd += read(GEN_CTL_FD, buf + rd, len1);
    if(rd != *len)
    {
        err_msg = "length inconsistent in receive_file()\n";
        exit(1);
    }
    
}
*/

//0 greet
//1 AFL ask for more mutants
//2 stop the current mutation and start mutating a new file
static int receive_ctl()
{
    int flag;
    read(GEN_CTL_FD, &flag, 4);
    return flag;
}

//send 0 to greet AFL
static void greet_AFL()
{
    int flag = 0;
    write(GEN_ST_FD, &flag, 4);
}

static void send_msg(int msg)
{
    write(GEN_ST_FD, &msg, 4);
}
/*
int fuzz_one(int argc, char *argv[]) {
  PDFDoc *doc;
  char *fileName;
  GString *ownerPW, *userPW;
  char buf[256];
  int i, j, k, type;
  XRef* xref = NULL;
  std::string s; 
  Object* obj_tmp;
  std::vector<Object*> objs, objs2;
  std::vector<Object> objs1;
  GBool ok;
  int fuzz_cnt = 0;
  int ctl;
  fixCommandLine(&argc, &argv);
  ok = parseArgs(argDesc, &argc, argv);
  if (!ok || argc != 2 || printVersion || printHelp) {
    fprintf(stderr, "pdfinfo version %s\n", xpdfVersion);
    fprintf(stderr, "%s\n", xpdfCopyright);
    if (!printVersion) {
      printUsage("pdfinfo", "<PDF-file>", argDesc);
    }
    goto err0;
  }
  fileName = argv[1];

  // open PDF file
  if (ownerPassword[0] != '\001') {
    ownerPW = new GString(ownerPassword);
  } else {
    ownerPW = NULL;
  }
  if (userPassword[0] != '\001') {
    userPW = new GString(userPassword);
  } else {
    userPW = NULL;
  }
  doc = new PDFDoc(fileName, ownerPW, userPW);
  
  if (userPW) {
    delete userPW;
  }
  if (ownerPW) {
    delete ownerPW;
  }
  

  xref = doc->getXRef();
  if(xref == NULL)
  {
      delete doc;
      goto err0;
  }
  objs = xref->get_all_objs();
  for(type = 0; type < 10; type++)
  {
    objs1 = objPool.get((ObjType)type);
    for(i = 0; i < objs1.size(); i++)
    {
      for(j = 0; j < objs.size(); j++)
      {
        if(objs[j] == NULL)
            continue;
        obj_tmp = objs[j];
        objs2 = objs[j]->mutate(&objs1[i]);
        fuzz_cnt += objs2.size();
        
        for(k = 0; k < objs2.size(); k++)
        {
          ctl = receive_ctl();
          //ask for fuzzing
          if(ctl == 1)
          {
            xref->objsSet(j, objs2[k]);
            s = xref->to_string();
            send_file(s.length(), (unsigned char*)s.c_str());
            objs2[k]->free();
            delete objs2[k];
          }
          //exit
          else if (ctl == -1)
          {
            break;
          }
          else
          {
              err_msg = "Unexpected message when mutating\n";
              exit(1);
          }
        }

        //check if exit early
        if(ctl == -1)
        {
          while(k < objs2.size())
          {
              objs2[k]->free();
              delete objs2[k];
              k++;
          }
          xref->objsSet(j, obj_tmp);
          goto early;
        }
        else
        {

            xref->objsSet(j, obj_tmp);
        }

        //if(fuzz_cnt > MUTATE_MAX)
        if(fuzz_cnt > MUTATE_MAX)
            goto normal;
      }
    }
  }
}
*/

int fuzz_one(int argc, char *argv[]) {
  PDFDoc *doc;
  char *fileName;
  GString *ownerPW, *userPW;
  char buf[256];
  int i, j, k, type;
  XRef* xref = NULL;
  std::string s; 
  Object* obj_tmp;
  std::vector<Object*> objs, objs2;
  std::vector<Object> objs1;
  GBool ok;
  int fuzz_cnt = 0;
  int ctl;
  int status = 0;
  fixCommandLine(&argc, &argv);
  ok = parseArgs(argDesc, &argc, argv);
  if (!ok || argc != 2 || printVersion || printHelp) {
    fprintf(stderr, "pdfinfo version %s\n", xpdfVersion);
    fprintf(stderr, "%s\n", xpdfCopyright);
    if (!printVersion) {
      printUsage("pdfinfo", "<PDF-file>", argDesc);
    }
    goto err0;
  }
  fileName = argv[1];

  // open PDF file
  if (ownerPassword[0] != '\001') {
    ownerPW = new GString(ownerPassword);
  } else {
    ownerPW = NULL;
  }
  if (userPassword[0] != '\001') {
    userPW = new GString(userPassword);
  } else {
    userPW = NULL;
  }
  doc = new PDFDoc(fileName, ownerPW, userPW);
  
  if (userPW) {
    delete userPW;
  }
  if (ownerPW) {
    delete ownerPW;
  }
  
  /*
  if (!doc->isOk()) {
    delete doc;
    goto err0;
  }
  */

  xref = doc->getXRef();
  if(xref == NULL)
  {
      delete doc;
      goto err0;
  }
  objs = xref->get_all_objs();
  for(i = 1; i < objs.size(); i++)
  {
      std::cout<<"  "<<i<<"/"<<objs.size() - 1<<std::endl;
      status = 0;
      fuzz_cnt += xref->mutate(i, &status);
      //exit early
      if(status != 0)
      {
        goto early;
      }
      //too many mutants
      if(fuzz_cnt > 100000)
      {
        break;
      }
  }
  std::cout<<"Generate "<<fuzz_cnt<<" files\n";

//send the last empty file
normal:  
  ctl = receive_ctl();
  if(ctl == 1)
  {
      //tell afl we have no more mutations
      send_msg(0);
  }
  else if(ctl == -1)
  {
    //do nothing
  }
  else
  {
     err_msg = "When finishing the mutation, unexpected command";
     exit(1);
  }

//do not send the last empty file
early:
  delete doc;  
  return 0;

//the file is not a valid pdf and we do not fuzz it
err0:
  ctl = receive_ctl();
  if(ctl != 1)
  {
      err_msg = "Wrong ctl\n";
      exit(1);
  }
  send_msg(0);
  return 1;
}

void KILLhandler(int sig)
{

}

void ABRThandler(int sig)
{
    FILE* fp = fopen("/tmp/xpdferror", "w");
    fprintf(fp, "error");
    fclose(fp);
}


std::vector<std::string> list_dir(const char* dirpath)
{
    DIR *dir;
    struct dirent *ent;
    std::vector<std::string> filenames;
    std::string s;
    if ((dir = opendir (dirpath)) != NULL) 
    {
        while ((ent = readdir (dir)) != NULL) 
        {
            if(!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, ".."))
                continue;
            s = dirpath;
            s += ent->d_name;
            filenames.push_back(s);
        }
        closedir (dir);
    } 
    else 
    {
        std::cout<<"Error in opendir()\n";
        exit(1);
    }
    return filenames;
}
/*
int genpdf(int argc, char *argv[]) {
  PDFDoc *doc;
  char *fileName;
  GString *ownerPW, *userPW;
  char buf[256];
  int i, j, k, type;
  XRef* xref = NULL;
  std::string s; 
  Object* obj_tmp;
  std::vector<Object*> objs, objs2;
  std::vector<Object> objs1;
  GBool ok;
  int fuzz_cnt = 0;
  fixCommandLine(&argc, &argv);
  ok = parseArgs(argDesc, &argc, argv);
  if (!ok || argc != 2 || printVersion || printHelp) {
    fprintf(stderr, "pdfinfo version %s\n", xpdfVersion);
    fprintf(stderr, "%s\n", xpdfCopyright);
    if (!printVersion) {
      printUsage("pdfinfo", "<PDF-file>", argDesc);
    }
    goto err0;
  }
  fileName = argv[1];

  // open PDF file
  if (ownerPassword[0] != '\001') {
    ownerPW = new GString(ownerPassword);
  } else {
    ownerPW = NULL;
  }
  if (userPassword[0] != '\001') {
    userPW = new GString(userPassword);
  } else {
    userPW = NULL;
  }
  doc = new PDFDoc(fileName, ownerPW, userPW);
  
  if (userPW) {
    delete userPW;
  }
  if (ownerPW) {
    delete ownerPW;
  }
  xref = doc->getXRef();
  if(xref == NULL)
  {
      delete doc;
      goto err0;
  }
  objs = xref->get_all_objs();
  for(type = 0; type < 10; type++)
  {
    objs1 = objPool.get((ObjType)type);
    for(i = 0; i <objs1.size(); i++)
    {
      for(j = 0; j < objs.size(); j++)
      {
        if(objs[j] == NULL)
            continue;
        obj_tmp = objs[j];
        objs2 = objs[j]->mutate(&objs1[i]);
        fuzz_cnt += objs2.size();

        for(k = 0; k < objs2.size(); k++)
        {
          xref->objsSet(j, objs2[k]);
          //s = xref->to_string();
          //std::cout<<objs2[k]->to_string()<<std::endl;
          objs2[k]->free();
          delete objs2[k];
        }
        xref->objsSet(j, obj_tmp);
        //std::cout<<"\n\n";
        if(fuzz_cnt > MUTATE_MAX)
        {
            //std::cout<<"Fuzzing max, exit\n";
            goto normal; 
        }
      }
    }
  }
normal:
  std::cout<<"gen "<<fuzz_cnt<<" files in total\n";
  delete doc;  
  return 0;
err0:
  return 1;
}
*/

int genpdf1(int argc, char *argv[]) {
  PDFDoc *doc;
  char *fileName;
  GString *ownerPW, *userPW;
  char buf[256];
  int i, j, k, type;
  XRef* xref = NULL;
  std::string s; 
  Object* obj_tmp;
  std::vector<Object*> objs, objs2;
  std::vector<Object> objs1;
  GBool ok;
  int fuzz_cnt = 0;
  int status = 0;
  fixCommandLine(&argc, &argv);
  ok = parseArgs(argDesc, &argc, argv);
  if (!ok || argc != 2 || printVersion || printHelp) {
    fprintf(stderr, "pdfinfo version %s\n", xpdfVersion);
    fprintf(stderr, "%s\n", xpdfCopyright);
    if (!printVersion) {
      printUsage("pdfinfo", "<PDF-file>", argDesc);
    }
    goto err0;
  }
  fileName = argv[1];

  // open PDF file
  if (ownerPassword[0] != '\001') {
    ownerPW = new GString(ownerPassword);
  } else {
    ownerPW = NULL;
  }
  if (userPassword[0] != '\001') {
    userPW = new GString(userPassword);
  } else {
    userPW = NULL;
  }
  doc = new PDFDoc(fileName, ownerPW, userPW);
  
  if (userPW) {
    delete userPW;
  }
  if (ownerPW) {
    delete ownerPW;
  }
  xref = doc->getXRef();
  if(xref == NULL)
  {
      delete doc;
      goto err0;
  }
  objs = xref->get_all_objs();
  for(i = 1; i < objs.size(); i++)
  {
      if(objs[i] == NULL)
          continue;
      std::cout<<"  "<<i<<"/"<<objs.size() - 1<<", type: "<<objs[i]->getType()<<std::endl;
      fuzz_cnt += xref->mutate(i, &status);
  }
  std::cout<<"Generate "<<fuzz_cnt<<" files\n";
normal:
  delete doc;  
  return 0;
err0:
  return 1;
}

#ifdef DEBUG_MODE
//pdftops -f 2 -l 4 -level2 -noembt1 -preload -nocrop -noshrink -nocenter -pagecrop -userunit -duplex -upw rome @@ /tmp/a.ps
int main(int argc, char *argv[])
{
    int i;
    double vm, rss;
    std::vector<std::string> filenames;
    char* argv_new[3];
    argv_new[0] = strdup(argv[0]);
    argv_new[2] = NULL;
    filenames = list_dir(argv[1]);
    std::string cmd1 = "/home/youwei/genpdf/hook/master/exe_raw/bin/pdftops";
    std::string cmd;
    std::string a_key;
    for(i = 0; i < filenames.size(); i++)
    {
        objPool.init();
        //read possible keys
        remove("/tmp/keys");
        cmd = cmd1 + filenames[i] + " /tmp/a.ps";
        system(cmd.c_str());
        std::ifstream fin("/tmp/keys");
        while(fin>>a_key)
        {
            objPool.insert_key(a_key);
        }
        std::cout<<"Processing "<<filenames[i]<<std::endl;
        argv_new[1] = strdup(filenames[i].c_str());
        genpdf1(2, argv_new);
        mem_usage(vm, rss);
        std::cout<<"VM: "<<rss<<" RSS: "<<rss<<", object pool size:"<<objPool.size()<<"\n\n";
        free(argv_new[1]);
        objPool.destroy();
    }
    free(argv_new[0]);
}
#else
int main(int argc, char* argv[])
{
    char file_name[] = "/tmp/.mutant";
    char* argv_new[3];
    int i;
    FILE *fp, *fp1, *fp_mem;
    int command;
    unsigned char* buf = new unsigned char[FILE_LENGTH_MAX];
    unsigned len;
    unsigned loop_cnt = 0;
    double vm, rss;    
    std::string cmd1 = "/home/youwei/genpdf/hook/master/exe_raw/bin/pdftops";
    std::string cmd;
    cmd = cmd1 + file_name + " /tmp/a.ps";
    std::string a_key;
    std::ifstream fin;
    //init objPool, create some basic object
    argv_new[0] = argv[0];
    argv_new[1] = file_name;
    argv_new[2] = NULL;
    //signal(SIGABRT, ABRThandler);
    atexit(dump_err);
    greet_AFL();
    setup_shm();
    remove("/tmp/mem_usage");
    //connect with AFL
    while(1)
    {
        mem_usage(vm, rss);
        fp_mem = fopen("/tmp/mem_usage", "a");
        fprintf(fp_mem, "%lf, %lf\n", vm, rss);
        fclose(fp_mem);
        //allow objPool use at most about 8G memory
        if(rss > 8000000)
            objPool.set_stop(true);
        command = receive_ctl();
        switch(command)
        {
            // fuzz a new file
            case 2:
                //receive command from AFL
                receive_file(&len, buf);
                if(len == -1 || len >= FILE_LENGTH_MAX)
                {
                    continue;
                }
                fp = fopen(file_name, "wb");
                fwrite(buf, 1, len, fp);
                fclose(fp);
                //tell AFL we receive the file
                send_msg(0);
                //init object pool
                objPool.init();
                //get keys
                remove("/tmp/keys");
                system(cmd.c_str());
                fin.open("/tmp/keys");
                while(fin>>a_key)
                {
                    objPool.insert_key(a_key);
                }
                fin.close();
                
                fuzz_one(2, argv_new);
                objPool.destroy();
                break;
            default:
                err_msg = "Unexpected command ";
                err_msg += std::to_string(command);
                exit(1);
                break;
        }
        loop_cnt++;
    }
    delete buf;
    return 0;
}
#endif
/*Modification End*/

/*Modification Begin*/
/*
int main(int argc, char *argv[]) {
  PDFDoc *doc;
  char *fileName;
  GString *ownerPW, *userPW;
  UnicodeMap *uMap;
  Page *page;
  Object info, xfa;
  Object *acroForm;
  char buf[256];
  double w, h, wISO, hISO;
  FILE *f;
  GString *metadata;
  ZxDoc *xmp;
  GBool ok;
  int exitCode;
  int pg, i;
  GBool multiPage;

  exitCode = 99;

  // parse args
  fixCommandLine(&argc, &argv);
  ok = parseArgs(argDesc, &argc, argv);
  if (!ok || argc != 2 || printVersion || printHelp) {
    fprintf(stderr, "pdfinfo version %s\n", xpdfVersion);
    fprintf(stderr, "%s\n", xpdfCopyright);
    if (!printVersion) {
      printUsage("pdfinfo", "<PDF-file>", argDesc);
    }
    goto err0;
  }
  fileName = argv[1];

  // read config file
  globalParams = new GlobalParams(cfgFileName);
  if (textEncName[0]) {
    globalParams->setTextEncoding(textEncName);
  }

  // get mapping to output encoding
  if (!(uMap = globalParams->getTextEncoding())) {
    error(errConfig, -1, "Couldn't get text encoding");
    goto err1;
  }

  // open PDF file
  if (ownerPassword[0] != '\001') {
    ownerPW = new GString(ownerPassword);
  } else {
    ownerPW = NULL;
  }
  if (userPassword[0] != '\001') {
    userPW = new GString(userPassword);
  } else {
    userPW = NULL;
  }
  doc = new PDFDoc(fileName, ownerPW, userPW);
  if (userPW) {
    delete userPW;
  }
  if (ownerPW) {
    delete ownerPW;
  }
  if (!doc->isOk()) {
    exitCode = 1;
    goto err2;
  }

  // get page range
  if (firstPage < 1) {
    firstPage = 1;
  }
  if (lastPage == 0) {
    multiPage = gFalse;
    lastPage = 1;
  } else {
    multiPage = gTrue;
  }
  if (lastPage < 1 || lastPage > doc->getNumPages()) {
    lastPage = doc->getNumPages();
  }

  // print doc info
  doc->getDocInfo(&info);
  if ((metadata = doc->readMetadata())) {
    xmp = ZxDoc::loadMem(metadata->getCString(), metadata->getLength());
  } else {
    xmp = NULL;
  }
  printInfoString(&info, "Title",        xmp, "dc:title",        NULL,              "Title:          ", gFalse,    uMap);
  printInfoString(&info, "Subject",      xmp, "dc:description",  NULL,              "Subject:        ", gFalse,    uMap);
  printInfoString(&info, "Keywords",     xmp, "pdf:Keywords",    NULL,              "Keywords:       ", gFalse,    uMap);
  printInfoString(&info, "Author",       xmp, "dc:creator",      NULL,              "Author:         ", gFalse,    uMap);
  printInfoString(&info, "Creator",      xmp, "xmp:CreatorTool", NULL,              "Creator:        ", gFalse,    uMap);
  printInfoString(&info, "Producer",     xmp, "pdf:Producer",    NULL,              "Producer:       ", gFalse,    uMap);
  printInfoString(&info, "CreationDate", xmp, "xap:CreateDate",  "xmp:CreateDate",  "CreationDate:   ", !rawDates, uMap);
  printInfoString(&info, "ModDate",      xmp, "xap:ModifyDate",  "xmp:ModifyDate",  "ModDate:        ", !rawDates, uMap);
  info.free();
  if (xmp) {
    delete xmp;
  }

  // print tagging info
  printf("Tagged:         %s\n",
	 doc->getStructTreeRoot()->isDict() ? "yes" : "no");

  // print form info
  if ((acroForm = doc->getCatalog()->getAcroForm())->isDict()) {
    acroForm->dictLookup("XFA", &xfa);
    if (xfa.isStream() || xfa.isArray()) {
      if (doc->getCatalog()->getNeedsRendering()) {
	printf("Form:           dynamic XFA\n");
      } else {
	printf("Form:           static XFA\n");
      }
    } else {
      printf("Form:           AcroForm\n");
    }
    xfa.free();
  } else {
    printf("Form:           none\n");
  }

  // print page count
  printf("Pages:          %d\n", doc->getNumPages());

  // print encryption info
  printf("Encrypted:      ");
  if (doc->isEncrypted()) {
    printf("yes (print:%s copy:%s change:%s addNotes:%s)\n",
	   doc->okToPrint(gTrue) ? "yes" : "no",
	   doc->okToCopy(gTrue) ? "yes" : "no",
	   doc->okToChange(gTrue) ? "yes" : "no",
	   doc->okToAddNotes(gTrue) ? "yes" : "no");
  } else {
    printf("no\n");
  }

  // print page size
  for (pg = firstPage; pg <= lastPage; ++pg) {
    w = doc->getPageCropWidth(pg);
    h = doc->getPageCropHeight(pg);
    if (multiPage) {
      printf("Page %4d size: %g x %g pts", pg, w, h);
    } else {
      printf("Page size:      %g x %g pts", w, h);
    }
    if ((fabs(w - 612) < 0.1 && fabs(h - 792) < 0.1) ||
	(fabs(w - 792) < 0.1 && fabs(h - 612) < 0.1)) {
      printf(" (letter)");
    } else {
      hISO = sqrt(sqrt(2.0)) * 7200 / 2.54;
      wISO = hISO / sqrt(2.0);
      for (i = 0; i <= 6; ++i) {
	if ((fabs(w - wISO) < 1 && fabs(h - hISO) < 1) ||
	    (fabs(w - hISO) < 1 && fabs(h - wISO) < 1)) {
	  printf(" (A%d)", i);
	  break;
	}
	hISO = wISO;
	wISO /= sqrt(2.0);
      }
    }
    printf(" (rotated %d degrees)", doc->getPageRotate(pg));
    printf("\n");
  } 

  // print the boxes
  if (printBoxes) {
    if (multiPage) {
      for (pg = firstPage; pg <= lastPage; ++pg) {
	page = doc->getCatalog()->getPage(pg);
	sprintf(buf, "Page %4d MediaBox: ", pg);
	printBox(buf, page->getMediaBox());
	sprintf(buf, "Page %4d CropBox:  ", pg);
	printBox(buf, page->getCropBox());
	sprintf(buf, "Page %4d BleedBox: ", pg);
	printBox(buf, page->getBleedBox());
	sprintf(buf, "Page %4d TrimBox:  ", pg);
	printBox(buf, page->getTrimBox());
	sprintf(buf, "Page %4d ArtBox:   ", pg);
	printBox(buf, page->getArtBox());
      }
    } else {
      page = doc->getCatalog()->getPage(firstPage);
      printBox("MediaBox:       ", page->getMediaBox());
      printBox("CropBox:        ", page->getCropBox());
      printBox("BleedBox:       ", page->getBleedBox());
      printBox("TrimBox:        ", page->getTrimBox());
      printBox("ArtBox:         ", page->getArtBox());
    }
  }

  // print file size
  f = openFile(fileName, "rb");
  if (f) {
    gfseek(f, 0, SEEK_END);
    printf("File size:      %u bytes\n", (Guint)gftell(f));
    fclose(f);
  }

  // print linearization info
  printf("Optimized:      %s\n", doc->isLinearized() ? "yes" : "no");

  // print PDF version
  printf("PDF version:    %.1f\n", doc->getPDFVersion());

  // print the metadata
  if (printMetadata && metadata) {
    fputs("Metadata:\n", stdout);
    fputs(metadata->getCString(), stdout);
    fputc('\n', stdout);
  }

  if (metadata) {
    delete metadata;
  }

  exitCode = 0;

  // clean up
 err2:
  uMap->decRefCnt();
  delete doc;
 err1:
  delete globalParams;
 err0:

  // check for memory leaks
  Object::memCheck(stderr);
  gMemReport(stderr);

  return exitCode;
}
*/
/*Modification End*/
static void printInfoString(Object *infoDict, const char *infoKey,
			    ZxDoc *xmp, const char *xmpKey1,
			    const char *xmpKey2,
			    const char *text, GBool parseDate,
			    UnicodeMap *uMap) {
  Object obj;
  TextString *s;
  Unicode *u;
  Unicode uu;
  char buf[8];
  GString *value, *tmp;
  ZxElement *rdf, *elem, *child;
  ZxNode *node, *node2;
  int i, n;

  value = NULL;

  //-- check the info dictionary
  if (infoDict->isDict()) {
    if (infoDict->dictLookup(infoKey, &obj)->isString()) {
      if (!parseDate || !(value = parseInfoDate(obj.getString()))) {
	s = new TextString(obj.getString());
	u = s->getUnicode();
	value = new GString();
	for (i = 0; i < s->getLength(); ++i) {
	  n = uMap->mapUnicode(u[i], buf, sizeof(buf));
	  value->append(buf, n);
	}
	delete s;
      }
    }
    obj.free();
  }

  //-- check the XMP metadata
  if (xmp) {
    rdf = xmp->getRoot();
    if (rdf->isElement("x:xmpmeta")) {
      rdf = rdf->findFirstChildElement("rdf:RDF");
    }
    if (rdf && rdf->isElement("rdf:RDF")) {
      for (node = rdf->getFirstChild(); node; node = node->getNextChild()) {
	if (node->isElement("rdf:Description")) {
	  if (!(elem = node->findFirstChildElement(xmpKey1)) && xmpKey2) {
	    elem = node->findFirstChildElement(xmpKey2);
	  }
	  if (elem) {
	    if ((child = elem->findFirstChildElement("rdf:Alt")) ||
		(child = elem->findFirstChildElement("rdf:Seq"))) {
	      if ((node2 = child->findFirstChildElement("rdf:li"))) {
		node2 = node2->getFirstChild();
	      }
	    } else {
	      node2 = elem->getFirstChild();
	    }
	    if (node2 && node2->isCharData()) {
	      if (value) {
		delete value;
	      }
	      if (!parseDate ||
		  !(value = parseXMPDate(((ZxCharData *)node2)->getData()))) {
		tmp = ((ZxCharData *)node2)->getData();
		int i = 0;
		value = new GString();
		while (getUTF8(tmp, &i, &uu)) {
		  n = uMap->mapUnicode(uu, buf, sizeof(buf));
		  value->append(buf, n);
		}
	      }
	    }
	    break;
	  }
	}
      }
    }
  }

  if (value) {
    fputs(text, stdout);
    fwrite(value->getCString(), 1, value->getLength(), stdout);
    fputc('\n', stdout);
    delete value;
  }
}

static GString *parseInfoDate(GString *s) {
  int year, mon, day, hour, min, sec, n;
  struct tm tmStruct;
  char buf[256];
  char *p;

  p = s->getCString();
  if (p[0] == 'D' && p[1] == ':') {
    p += 2;
  }
  if ((n = sscanf(p, "%4d%2d%2d%2d%2d%2d",
		  &year, &mon, &day, &hour, &min, &sec)) < 1) {
    return NULL;
  }
  switch (n) {
  case 1: mon = 1;
  case 2: day = 1;
  case 3: hour = 0;
  case 4: min = 0;
  case 5: sec = 0;
  }
  tmStruct.tm_year = year - 1900;
  tmStruct.tm_mon = mon - 1;
  tmStruct.tm_mday = day;
  tmStruct.tm_hour = hour;
  tmStruct.tm_min = min;
  tmStruct.tm_sec = sec;
  tmStruct.tm_wday = -1;
  tmStruct.tm_yday = -1;
  tmStruct.tm_isdst = -1;
  // compute the tm_wday and tm_yday fields
  if (!(mktime(&tmStruct) != (time_t)-1 &&
	strftime(buf, sizeof(buf), "%c", &tmStruct))) {
    return NULL;
  }
  return new GString(buf);
}

static GString *parseXMPDate(GString *s) {
  int year, mon, day, hour, min, sec, tz;
  struct tm tmStruct;
  char buf[256];
  char *p;

  p = s->getCString();
  if (isdigit(p[0]) && isdigit(p[1]) && isdigit(p[2]) && isdigit(p[3])) {
    buf[0] = p[0];
    buf[1] = p[1];
    buf[2] = p[2];
    buf[3] = p[3];
    buf[4] = '\0';
    year = atoi(buf);
    p += 4;
  } else {
    return NULL;
  }
  mon = day = 1;
  hour = min = sec = 0;
  tz = 2000;
  if (p[0] == '-' && isdigit(p[1]) && isdigit(p[2])) {
    buf[0] = p[1];
    buf[1] = p[2];
    buf[2] = '\0';
    mon = atoi(buf);
    p += 3;
    if (p[0] == '-' && isdigit(p[1]) && isdigit(p[2])) {
      buf[0] = p[1];
      buf[1] = p[2];
      buf[2] = '\0';
      day = atoi(buf);
      p += 3;
      if (p[0] == 'T' && isdigit(p[1]) && isdigit(p[2]) &&
	  p[3] == ':' && isdigit(p[4]) && isdigit(p[5])) {
	buf[0] = p[1];
	buf[1] = p[2];
	buf[2] = '\0';
	hour = atoi(buf);
	buf[0] = p[4];
	buf[1] = p[5];
	buf[2] = '\0';
	min = atoi(buf);
	p += 6;
	if (p[0] == ':' && isdigit(p[1]) && isdigit(p[2])) {
	  buf[0] = p[1];
	  buf[1] = p[2];
	  buf[2] = '\0';
	  sec = atoi(buf);
	  if (p[0] == '.' && isdigit(p[1])) {
	    p += 2;
	  }
	}
	if ((p[0] == '+' || p[0] == '-') &&
	    isdigit(p[1]) && isdigit(p[2]) && p[3] == ':' &&
	    isdigit(p[4]) && isdigit(p[5])) {
	  buf[0] = p[1];
	  buf[1] = p[2];
	  buf[2] = '\0';
	  tz = atoi(buf);
	  buf[0] = p[4];
	  buf[1] = p[5];
	  buf[2] = '\0';
	  tz = tz * 60 + atoi(buf);
	  tz = tz * 60;
	  if (p[0] == '-') {
	    tz = -tz;
	  }
	}
      }
    }
  }

  tmStruct.tm_year = year - 1900;
  tmStruct.tm_mon = mon - 1;
  tmStruct.tm_mday = day;
  tmStruct.tm_hour = hour;
  tmStruct.tm_min = min;
  tmStruct.tm_sec = sec;
  tmStruct.tm_wday = -1;
  tmStruct.tm_yday = -1;
  tmStruct.tm_isdst = -1;
  // compute the tm_wday and tm_yday fields
  //~ this ignores the timezone
  if (!(mktime(&tmStruct) != (time_t)-1 &&
	strftime(buf, sizeof(buf), "%c", &tmStruct))) {
    return NULL;
  }
  return new GString(buf);
}

static void printBox(const char *text, PDFRectangle *box) {
  printf("%s%8.2f %8.2f %8.2f %8.2f\n",
	 text, box->x1, box->y1, box->x2, box->y2);
}
