(define/contract (percentage-letter s letter)
  (-> string? char? exact-integer?)
  (let* ([chars (string->list s)]
         [total (length chars)]
         [count (for/sum ([c chars])
                  (if (char=? c letter) 1 0))])
    (if (= total 0)
        0
        (floor (/ (* count 100) total)))))
