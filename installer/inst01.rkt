#lang racket

(define (run-file-dir)
  (let*-values
      ([(%run-file)
        (simplify-path (path->complete-path (find-system-path 'run-file)))]
       [(%base %name %must-be-dir?) (split-path %run-file)])
    %base))

(define (run-with-curl %cmd)
  (let* ([%cmd1 (build-path (run-file-dir) "curl32.exe")]
         [%cmd2 (format "\"~a\" ~a" %cmd1 %cmd)])
    (printf "~a\n" %cmd2)
    (system/exit-code %cmd2)))

(define (run-with-busybox %cmd)
  (let* ([%cmd1 (build-path (run-file-dir) "busybox32.exe")]
         [%cmd2 (format "\"~a\" ~a" %cmd1 %cmd)])
    (printf "~a\n" %cmd2)
    (system/exit-code %cmd2)))

(system/exit-code "cmd.exe /c \"dir\"")
(define $curl (build-path (run-file-dir) "curl32.exe"))
;(run-with-curl "--etag-compare test.etag --etag-save test.etag -o msys2-x86_64-latest.tar.xz https://repo.msys2.org/distrib/msys2-x86_64-latest.tar.xz")
(run-with-busybox
 (format
  "time \"~a\" --etag-compare test.etag --etag-save test.etag -o msys2-x86_64-latest.tar.xz https://repo.msys2.org/distrib/msys2-x86_64-latest.tar.xz"
  $curl
  ))
(run-with-busybox "time rm -rf my-msys2.tmp")
(run-with-busybox "time mkdir -p my-msys2.tmp")
(run-with-busybox "time tar -xf msys2-x86_64-latest.tar.xz -C my-msys2.tmp --strip-components 1")
