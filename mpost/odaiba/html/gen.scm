#!/usr/bin/env guile
!#

(define-macro pl
  (lambda body
    `(begin (map display (list ,@body))
            (newline))))

(define (tag p body)
  (pl "<" p ">")
  (body)
  (pl "</" p ">"))

(define (lazy expr)
  (lambda () (expr)))

(define (html body)
  (pl "<!doctype html>")
  (tag "html" (lazy body)))

(define (img src)
  (pl "<img src=\"svg-" src ".svg\"/>"))

(define (main)
  (html (lambda ()
	  (tag "head" (lambda ()
			(tag "title" (lambda () (display "rx-78-2")))))
	  (tag "body" (lambda () (map img imgs))))))

(define imgs '(0 1 2
                 118
                 101
                 102
                 107
                 103
                 104
                 119
                 105
                 108
                 121
                 109))

(main)
