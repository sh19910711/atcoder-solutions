require 'scanf'

def solve(a, n, k)
  res = 0
  if k == 1
    res = 1
  end
  b = a.map {|x| 0 }
  (n-1).times {|i| b[i] = a[i] < a[i + 1] ? 1 : 0 }
  s = a.map {|x| 0 }
  sum = 0
  (n-1).times {|i|
    if b[i] == 0
      s[i] = b[i]
      sum = 0
    else
      s[i] = sum + b[i]
    end
    if s[i] - k + 1 >= 0
      res += 1
    end
    sum += b[i]
  }
  res
end

n, k = gets.scanf "%d%d"
a = []
n.times {|x| a.push gets.to_i }

puts solve(a, n, k)

