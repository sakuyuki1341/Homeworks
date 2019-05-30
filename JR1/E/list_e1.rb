$balance = 0

def initialize_balance
  $balance = 0
end

def get_balance
  return $balance
end

def deposit(x)
  $balance += x
end

def withdraw(x)
  if x <= $balance
    $balance -= x
  else
    $balance = 0
  end
end
