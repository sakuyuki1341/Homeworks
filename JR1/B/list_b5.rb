def coban(x, a1, a2, b1, b2, c1, c2)
  pe = 0
  ap = 0
  bp = 0
  cp = 0
  if (a1 > x) || (a2 < x)
    pe = pe + 1; ap = 1
  end
  if (b1 > x) || (b2 < x)
    pe = pe + 1; bp = 1
  end
  if (c1 > x) || (c2 < x)
    pe = pe + 1; cp = 1
  end
  if (pe == 0) || (pe > 1)
    puts 'D'
  else
    if ap == 1
      puts 'A'
    elsif bp == 1
      puts 'B'
    else
      puts 'C'
    end
  end
end
