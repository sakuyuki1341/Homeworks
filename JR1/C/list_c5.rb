def num_primefactors(n)
  $n_new = n
  $ret = 0
  $max = Math.sqrt(n)
  return calc(n)
end
def calc(n)
  i = 1
  if $n_new == 1
    return $ret
  end
  while $n_new == n do
    if $max <= i
      return $ret + 1
    end
    i += 1
    if (n % i) == 0
      $ret +=  1
      $n_new = n / i
    end
#    puts i             デバッグ用
  end
  return calc($n_new)
end
