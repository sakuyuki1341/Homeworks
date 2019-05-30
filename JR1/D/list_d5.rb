def janken(n, arr1, arr2)
  win = 0
  loss = 0
  draw = 0
  n.times do |i|
    if arr1[i] == arr2[i]
      draw = draw + 1
    elsif arr1[i] - arr2[i] == -1 || arr1[i] - arr2[i] == 2
      win = win + 1
    else
      loss = loss + 1
    end
  end
  printf("Total: %d, Win: %d, Loss: %d, Draw: %d\n", n, win, loss, draw)
end
