require 'scanf' 

@list = [("A".."Z").to_a, ("a".."z").to_a].flatten
def get_alphabet id
  @list[id]
end

while s = gets
  n, k = s.scanf "%d%d"
  (1..52).each do |x|
    if x * k >= n - x
      # puts "x = #{x}, n = #{n}, k = #{k}"
      puts "#{k+2} #{x * k}"
      cnt = 0
      w = x * k
      x.times do
        puts get_alphabet(cnt) * k
        cnt += 1
      end
      if cnt >= n
        break
      end
      tmp = cnt
      puts get_alphabet(cnt) + "." * ( w - 1 )
      remains = [0, n - 1 - tmp - 1].max
      p remains
      (k-1).times do
        puts (tmp..n-1).to_a.map {|v| get_alphabet(v) }.join + ( "." * remains )
      end
      puts "." + (tmp+1..n-1).to_a.map {|v| get_alphabet(v) }.join + ( "." * remains )
      break
    end
  end
end
