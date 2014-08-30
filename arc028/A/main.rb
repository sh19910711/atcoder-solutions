def solve(t, n, a, b)
  return t if n <= 0
  return solve(1 - t, n - ( t == 0 ? a : b ), a, b)
end

puts ( solve(0, *gets.split.map(&:to_i)) == 0 ? "Bug" : "Ant" )
