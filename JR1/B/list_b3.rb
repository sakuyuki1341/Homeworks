def bmi_category(h, w)
  bmi = w / h**2
  if bmi < 18.5
    puts 'Low'
  elsif bmi < 25
    puts 'Normal'
  elsif bmi < 30
    puts 'Obese (Level 1)'
  elsif bmi < 35
    puts 'Obese (Level 2)'
  elsif bmi < 40
    puts 'Obese (Level 3)'
  else
    puts 'Obese (Level 4)'
  end
end
