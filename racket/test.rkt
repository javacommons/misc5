#! racket32
#lang racket

(require ffi/com)

(define (get-registry-env %scope %name)
  (let* ([%wshell (com-create-instance "WScript.Shell" 'local)]
         [%env (com-get-property* %wshell "Environment" %scope)]
         [%result (com-get-property %env (list "Item" %name))])
    (com-release %wshell)
    %result))

(define (set-registry-env! %scope %name %value)
  (let* ([%wshell (com-create-instance "WScript.Shell" 'local)]
         [%env (com-get-property* %wshell "Environment" %scope)])
    (com-set-property! %env (list "Item" %name) %value)
    (com-release %wshell)
    (get-registry-env %scope %name)))

(define (delete-registry-env! %scope %name)
  (let* ([%wshell (com-create-instance "WScript.Shell" 'local)]
         [%env (com-get-property* %wshell "Environment" %scope)]
         [%result #t])
    (with-handlers ([exn:fail? (lambda (%exn) (set! %result #f))])
      (com-invoke %env "Remove" %name))
    (com-release %wshell)
    %result))

(delete-registry-env! "USER" "XYZ")

;  (begin
;    (displayln "First line")
;    (call-with-exception-handler (lambda (x) (displayln "Exception handler")) (lambda () (error "Some error")))
;    (displayln "This line is not printed"))



