(setq inhibit-startup-message t)
(setq-default make-backup-files nil)

(load "~/c-quick-2.el")

(require 'package)
(setq package-archives
      '(("gnu" . "http://elpa.gnu.org/packages/")
        ("melpa" . "http://melpa.org/packages/")
        ("org" . "http://orgmode.org/elpa/")))
(package-initialize)
(unless package-archive-contents (package-refresh-contents))
(unless (package-installed-p 'use-package)
    (package-install 'use-package))

(use-package racket-mode
	     :ensure t
	     :pin melpa)
(add-to-list 'auto-mode-alist '("\\.rkt\\'" . racket-mode))
