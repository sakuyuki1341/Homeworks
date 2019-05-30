def bike_class(d)
  if d <= 50
    puts 'GENDOUKITSUKI-JITENSHA'
  elsif d <= 125
    puts 'KOGATA-JIDOU-NIRINSHA'
  elsif d <= 400
    puts 'FUTSU-JIDOU-NIRINSHA'
  else
    puts 'OHGATA-JIDOU-NIRINSHA'
  end
end
