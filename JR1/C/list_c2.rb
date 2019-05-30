def calc_a(a,n)
  $an = a
  if (n == 1)
    printf("%.5f", $an)
  else
    (n-1).times do |i|
      $an = 2*Math.sqrt($an)
    end
    printf("%.5f", $an)
  end
end
