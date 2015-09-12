require "prime"

def sum(s)
  s.split("").map(&:to_i).inject(0) { |x, y| x + y }
end

def ok?(x)
  ( x % 2 != 0 ) && ( x != 5 )
end

def solve(s)
  return "Not Prime" if s.to_i == 1
  if Prime.prime?(s.to_i)
    "Prime"
  else
    if ok?(s[-1].to_i) && sum(s) % 3 != 0
      "Prime"
    else
      "Not Prime"
    end
  end
end

puts solve(gets.strip) 

