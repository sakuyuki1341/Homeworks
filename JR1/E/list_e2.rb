def initialize_vending_machine
  $num_cans = 5
  $payment = 0
  ret = [$num_cans, $payment]
  return ret
end

def show_vending_machine
  ret = [$num_cans, $payment]
  return ret
end

def pay(x)
  $payment += x
  ret = [$num_cans, $payment]
  return ret
end

def pay_back
  $payment = 0
  ret = [$num_cans, $payment]
  return ret
end

def buy
  if $payment >= 200 && $num_cans >= 1
    $num_cans -= 1
    $payment -= 200
  end
  ret = [$num_cans, $payment]
  return ret
end
