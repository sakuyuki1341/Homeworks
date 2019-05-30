def initialize_array
  $arr = Array.new
  return $arr
end

def get_array
  return $arr
end

def append(x)
  $arr.push(x)
  return $arr
end

def swap(i, j)
  if $arr.length <= i || $arr.length <= j
    return $arr
  end
  first = $arr[i]
  $arr[i] = $arr[j]
  $arr[j] = first
  return $arr
end
