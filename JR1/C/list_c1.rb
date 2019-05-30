$c = 0.0
def harmonic(n)
  n.times do |i|
    $c = $c + 1.0/(i+1)
  end
  return $c
end
