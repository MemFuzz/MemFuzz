((nil . ((indent-tabs-mode . nil)
         (qpdf-cc-style
          .
          ("qpdf"
           (c-basic-offset . 4)
           (c-comment-only-line-offset . 0)
           (c-offsets-alist
            (defun-block-intro . +)
            (block-open . 0)
            (substatement-open . 0)
            (statement-cont . +)
            (case-label . 0)
            (access-label . -2)
            (statement-case-intro . +)
            (statement-case-open . +)
            (arglist-intro . +)
            (arglist-close . 0)
            (inline-open . 0)
            (inlambda . 0)
           )
          )
         )
         (c-noise-macro-names
	  . ("QPDF_DLL" "QPDF_DLL_CLASS" "QPDF_DLL_PRIVATE"))
        )
 )
 (c++-mode . ((eval . (progn
                        (add-to-list 'c-style-alist qpdf-cc-style)
                        (c-set-style "qpdf")
                      )
              ))
 )
 (c-mode . ((eval . (progn
                      (add-to-list 'c-style-alist qpdf-cc-style)
                      (c-set-style "qpdf")
                    )
            ))
 )
)
