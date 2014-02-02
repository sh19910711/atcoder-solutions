while s = gets
  n = s.to_i
  table = (1..n).map {|x| (1..n).map{|y| '.'}.join }
  if n <= 3
    puts -1
  elsif n == 8
    puts <<"EOF"
........
........
...##...
..#..#..
..#..#..
...##...
........
........
EOF
  else
    table[0][0] = '#' if n % 2 == 1
    (1..n/2).each {|x| table[x][x-1] = table[x-1][x] = '#'}
    table.each {|line| puts line }
  end
end
