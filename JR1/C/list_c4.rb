def sep2dec(n)
  $k = [0,0,0,0,0,0,0,0]
  ans = 0
  sum = 0
  8.times do |i|
    $k[8-i] = (n-sum)/10**(8-i)
    sum += $k[8-i]*10**(8-i)
  end
  $k[0] = n-sum
  8.times do |h|
    ans += $k[h]*7**h
  end
  return ans
end
