#lang racket

(require json)

(jsexpr? 'null)
(jsexpr? #t)
(jsexpr? "cheesecake")
(jsexpr? 3.5)
(jsexpr? (list 18 'null #f))
(jsexpr? #hasheq((turnip . 82)))
(jsexpr? (vector 1 2 3 4))
(jsexpr? #hasheq(("turnip" . 82)))
(jsexpr? +inf.0)

(string->jsexpr "null")
(jsexpr->string	 null)
(jsexpr->string	 'null)

(define (encode-input $name $value)
  (let* ([$input (hash 'name $name 'value $value)]
	 [$json (jsexpr->string $input)])
    $json))

(encode-input "name1" '(1 2 3))
