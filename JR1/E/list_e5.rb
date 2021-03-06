def initialize_board(n)
  $board = Array.new(2*n + 1)
  n.times do |i|
    $board[i] = 1
    $board[2*n - i] = 2
  end
  $board[n] = 0
  return $board
end

def move(i)
  if $board[i] == 0
    return $board
  elsif $board[i] == 1
    flag_0 = false
    flag_1 = true
    number = 0
    2.times do |j|
      if $board[i+j+1] == 0
        flag_0 = true
        number = i+j+1
      elsif $board[i+j+1] == 1 && flag_0 == false
        flag_1 = false
      end
    end
    if flag_0 && flag_1
      $board[number] = 1
      $board[i] = 0
    end
    return $board
  elsif $board[i] == 2
    flag_0 = false
    flag_2 = true
    number = 0
    2.times do |j|
      if $board[i - 1 - j] == 0
        flag_0 = true
        number = i - 1 - j
      elsif $board[i - 1 - j] == 2 && flag_0 == false
        flag_2 = false
      end
    end
    if flag_0 && flag_2
      $board[number] = 2
      $board[i] = 0
    end
    return $board
  end
end
