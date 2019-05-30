def digits(n)
  k1 = n / 100
  k2 = (n - k1 * 100) / 10
  k3 = n - k1 * 100 - k2 * 10
  printf("%d %d %d\n",k1 , k2, k3) 
end
