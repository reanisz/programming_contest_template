use strict;
use warnings;
use Data::Printer;
use File::Slurp;
use Text::Diff 'diff';

sub sh{
    my $script = shift;
    open(FILE, "-|", $script);
    my $ret = "";
    while(<FILE>){
        $ret .= $_;
    }
    close(FILE);
    return $ret;
}

my $target = shift @ARGV;

system("g++ $target.cpp -o $target -std=c++11") && die("compile error");

foreach my $i(map {$_=~m|$target(\d+).in|; $1} grep {$_=~m|$target(\d+).in|} read_dir("./")){
    print "==TEST $i==\n";
    my $out = sh("./$target < $target$i.in");
    my $correct = read_file("$target$i.out");
    if($out eq $correct){
        print "OK\n";
    }else{
        print "NG\n";
        print diff(\$out, \$correct);
    }
}

