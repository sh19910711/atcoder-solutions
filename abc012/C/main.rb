n = gets.to_i
l = (->(a){ a.product a }).call((1..9).to_a)
s = l.reduce(0) {|s, t| s += t[0] * t[1]}
l.select {|t| t[0] * t[1] == s - n }.each {|t| puts "#{t[0]} x #{t[1]}"}