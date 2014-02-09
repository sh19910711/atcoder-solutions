require 'prime'
n = gets.to_i
if Prime.prime_division(n).flatten.length == 2
  puts "YES"
else
  puts "NO"
end
