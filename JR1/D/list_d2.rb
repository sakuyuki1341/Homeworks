def prefix_sum(a)
  b = Array.new(a.length, 0)
  a.length.times do |i|
    (i + 1).times do |j|
      b[i] = b[i] + a[j]
    end
  end
  return b
end
