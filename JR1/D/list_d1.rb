def missing_num(arr)
  sum = 0;
  arr.length.times do |i|
    sum += arr[i]
  end
  return 45 - sum
end
