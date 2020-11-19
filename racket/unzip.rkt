#lang racket

(require file/unzip)
(require ffi/com)

(define prepare-dir%
  (class
   object%
   (init :root-dir :zip-path)
   (super-new)
   (println :root-dir)
   (define %target-dir (build-path :root-dir ".software/racket-7.9-64bit"))
   (println %target-dir)
   (define %file-in (open-input-file :zip-path #:mode 'binary))
   (println %file-in)
   (cond
    [(not (directory-exists? %target-dir))
     (make-directory* %target-dir)
     (current-directory %target-dir)
     (current-directory)
     (println "unzip start")
     (unzip %file-in)
     (println "unzip end")])
   (define/public (result)
     %target-dir)
   )
  )

(define $home-dir (find-system-path 'home-dir))
$home-dir

(define $pd (new prepare-dir%
		 [:root-dir $home-dir]
		 [:zip-path "racket-7.9-64bit.zip"]))
(define $target-dir (send $pd result))
$target-dir


(define (get-registry-env scope name)
  (let* ([wshell (com-create-instance "WScript.Shell" 'local)]
         [env (com-get-property* wshell "Environment" scope)]
         [result (com-get-property env (list "Item" name))])
    (com-release wshell)
    result))

(define (set-registry-env! scope name value)
  (let* ([wshell (com-create-instance "WScript.Shell" 'local)]
         [env (com-get-property* wshell "Environment" scope)])
    (com-set-property! env (list "Item" name) value)
    (com-release wshell)
    (get-registry-env scope name)))


(define $path (get-registry-env "USER" "PATH"))
;(set-registry-env! "USER" "PATH2" (format "~a;~a" path "X:\\somewhere"))

(define $target-str (string-replace (path->string $target-dir) "/" "\\"))
$target-str
$path
(define $path-list (string-split $path ";"))
$path-list
(set! $path-list (cons $target-str $path-list))
$path-list
(if (member $target-str $path-list) (println "<is member>") #f)
(string-join $path-list ";")

(define set-path%
  (class
   object% (super-new)
   (init :member)
   (define %member (if (path? :member) (path->string :member) :member))
   (println %member)
   (set! %member (string-replace %member "/" "\\"))
   (println %member)
   (define %path (get-registry-env "USER" "PATH"))
   (println %path)
   (define %path-list (string-split $path ";"))
   (println %path-list)
   (set! %path-list (cons %member %path-list))
   (set! %path-list (remove-duplicates %path-list equal?))
   (println %path-list)
   (set! %path (string-join %path-list ";"))
   (println %path)
   (set-registry-env! "USER" "PATH" %path)
   )
  )

(new set-path% [:member $target-dir])
