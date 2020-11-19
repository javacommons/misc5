#lang racket

(find-system-path 'run-file)
(define $path (find-system-path 'run-file))
(resolve-path $path)
(define $abs-path (path->complete-path $path))
$abs-path
(split-path $abs-path)

(define $home-dir (find-system-path 'home-dir))
$home-dir

(find-system-path 'pref-dir)
(define $sendto-dir (build-path $home-dir "AppData\\Roaming\\Microsoft\\Windows\\SendTo"))
$sendto-dir

(directory-list $sendto-dir #:build? #t)
(directory-list $sendto-dir #:build? #f)

(require ffi/com)

(define create-simple-shortcut%
  (class object% (super-new)
    (init :shortcut-path :target-path)
    (define $wshell (com-create-instance "WScript.Shell" 'local))
    (define $sc (com-invoke $wshell "CreateShortcut" :shortcut-path))
    (com-set-property! $sc "TargetPath" :target-path)
    (com-invoke $sc "Save")
    )
  )

(define $shortcut-path (path->string (build-path $sendto-dir "Notepad.lnk")))
(new create-simple-shortcut%
     [:shortcut-path $shortcut-path]
     [:target-path "C:\\Windows\\System32\\notepad.exe"])
