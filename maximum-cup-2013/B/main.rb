require "prime"

while n = gets.to_i do
  break if n == 0
  puts Prime.prime_division(n).last[0]
end
