#lang racket

(require file/unzip)
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

(define (run-file-dir)
  (let*-values
      ([(%run-file)
        (simplify-path (path->complete-path (find-system-path 'run-file)))]
       [(%base %name %must-be-dir?) (split-path %run-file)])
    %base))

(define prepare-dir%
  (class object%
    (init :root-dir :zip-base) (super-new)
    (println :root-dir)
    (define &software-dir (build-path :root-dir ".software"))
    (define &target-dir (build-path &software-dir :zip-base))
    (println &target-dir)
    (define &run-file-dir (run-file-dir))
    (define &zip-path (format "~a\\~a.zip" &run-file-dir :zip-base))
    (define &file-in (open-input-file &zip-path #:mode 'binary))
    (println &file-in)
    (cond
      [(not (directory-exists? &target-dir))
       (make-directory* &target-dir)
       (current-directory &target-dir)
       (current-directory)
       (println "unzip start")
       (unzip &file-in)
       (println "unzip end")])
    (define/public (:get-target-dir)
      &target-dir)
    )
  )

(define set-path%
  (class object%
    (init :member) (super-new)
    (define &member (if (path? :member) (path->string :member) :member))
    (println &member)
    (set! &member (string-replace &member "/" "\\"))
    (println &member)
    (define &path (get-registry-env "USER" "PATH"))
    (println &path)
    (define &path-list (string-split &path ";"))
    (println &path-list)
    (set! &path-list (cons &member &path-list))
    (set! &path-list (remove-duplicates &path-list equal?))
    (println &path-list)
    (set! &path (string-join &path-list ";"))
    (println &path)
    (set-registry-env! "USER" "PATH" &path)
    )
  )

(define fix-path%
  (class object%
    (init) (super-new)
    (define &path (get-registry-env "USER" "PATH"))
    (println &path)
    (define &path-list (string-split &path ";"))
    (println &path-list)
    (set! &path-list (filter (lambda (%x) (or (string-contains? %x "%") (directory-exists? %x))) &path-list))
    (println &path-list)
    (set! &path (string-join &path-list ";"))
    (println &path)
    (set-registry-env! "USER" "PATH" &path)
    )
  )

(define create-simple-shortcut%
  (class object% (super-new)
    (init :shortcut-path :target-path)
    (define &wshell (com-create-instance "WScript.Shell" 'local))
    (define &sc (com-invoke &wshell "CreateShortcut" :shortcut-path))
    (com-set-property! &sc "TargetPath" :target-path)
    (com-invoke &sc "Save")
    )
  )

(provide
 get-registry-env
 set-registry-env!
 delete-registry-env!
 run-file-dir
 prepare-dir%
 set-path%
 fix-path%
 create-simple-shortcut%)