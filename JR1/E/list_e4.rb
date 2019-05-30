def initialize_bucket
  $bucket = [0, 0]
  $bucket_max = [4, 7]
  return $bucket
end

def empty(i)
  $bucket[i] = 0
  return $bucket
end

def fill(i)
  if i == 0
    $bucket[i] = $bucket_max[i]
  elsif i == 1
    $bucket[i] = $bucket_max[i]
  end
  return $bucket
end

def transfer(i)
  if i == 0
    trans_able = $bucket_max[1] - $bucket[1]
    if trans_able <= $bucket[0]
      $bucket[0] -= trans_able
      $bucket[1] = $bucket_max[1]
    else
      $bucket[1] += $bucket[0]
      $bucket[0] = 0
    end
    return $bucket
  elsif i == 1
    trans_able = $bucket_max[0] - $bucket[0]
    if trans_able <= $bucket[1]
      $bucket[1] -= trans_able
      $bucket[0] = $bucket_max[0]
    else
      $bucket[0] += $bucket[1]
      $bucket[1] = 0
    end
    return $bucket
  end
end
