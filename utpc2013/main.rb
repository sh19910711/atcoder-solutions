s = gets.strip

res = true
res &= "CEFGHIJKLMNSTUVWXYZ".split("").to_a.any? {|c| c == s[0] }
res &= "CEFGHIJKLMNSTUVWXYZ".split("").to_a.any? {|c| c == s[1] }
res &= "ADOPQR".split("").to_a.any? {|c| c == s[2] }
res &= "CEFGHIJKLMNSTUVWXYZ".split("").to_a.any? {|c| c == s[3] }

if res
  puts "yes"
else
  puts "no"
end

