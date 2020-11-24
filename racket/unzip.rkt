#! racket32
#lang racket

(require file/unzip)

(define $void (void))
(define $file-in (open-input-file "msys64.zip" #:mode 'binary))
(define $zipdir (read-zip-directory $file-in))
(define $entries (zip-directory-entries $zipdir))
(make-directory* "zip.tmp")
(current-directory "zip.tmp")
(for ([$entry $entries])
  (println $entry)
  (unzip-entry $file-in $zipdir $entry #:preserve-timestamps? #t))
