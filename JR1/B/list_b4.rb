def zodiac(m, d)
  if ((m == 3) && (d >= 21) && (d <= 31)) || ((m == 4) && (d <= 19) && (d >= 1))
    puts 'Aries'
  elsif ((m == 4) && (d >= 20) && (d <= 30)) || ((m == 5) && (d <= 20) && (d >= 1))
    puts 'Taurus'
  elsif ((m == 5) && (d >= 21) && (d <= 31)) || ((m == 6) && (d <= 21) && (d >= 1))
    puts 'Gemini'
  elsif ((m == 6) && (d >= 22) && (d <= 30)) || ((m == 7) && (d <= 22) && (d >= 1))
    puts 'Cancer'
  elsif ((m == 7) && (d >= 23) && (d <= 31)) || ((m == 8) && (d <= 22) && (d >= 1))
    puts 'Leo'
  elsif ((m == 8) && (d >= 23) && (d <= 31)) || ((m == 9) && (d <= 22) && (d >= 1))
    puts 'Virgo'
  elsif ((m == 9) && (d >= 23) && (d <= 30)) || ((m == 10) && (d <= 23) && (d >= 1))
    puts 'Libra'
  elsif ((m == 10) && (d >= 24) && (d <= 31)) || ((m == 11) && (d <= 22) && (d >= 1))
    puts 'Scorpio'
  elsif ((m == 11) && (d >= 23) && (d <= 30)) || ((m == 12) && (d <= 21) && (d >= 1))
    puts 'Sagittarius'
  elsif ((m == 12) && (d >= 22) && (d <= 31)) || ((m == 1) && (d <= 19) && (d >= 1))
    puts 'Capricorn'
  elsif ((m == 1) && (d >= 20) && (d <= 31)) || ((m == 2) && (d <= 18) && (d >= 1))
    puts 'Aquarius'
  elsif ((m == 2) && (d >= 19) && (d <= 29)) || ((m == 3) && (d <= 20) && (d >= 1))
    puts 'Pisces'
  else
    puts 'X'
  end
end
