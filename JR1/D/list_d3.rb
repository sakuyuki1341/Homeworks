def has_duplicates?(arr)
  arr.length.times do |i|
    arr.length.times do |j|
      sum = 0
      sum += arr[i]
      if i != j
        sum += arr[j]
        if sum  == 0
          return true
        end
      end
    end
  end
  return false
end
