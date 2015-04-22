use strict;
use warnings;

use utf8;

my %flag;

sub run{
    my $dir = shift;
    my $fn = shift;
    my $n = "$dir/$fn";
    my $res = "";
    open(my $file, '<' , $n);
    while(my $line = <$file>){
        if($line =~ m|^//|){
        }elsif($line =~ /\#pragma once/){
            if($flag{$n} == 1){
                last;
            }
        }elsif($line =~ /^\#include\s+\"(.*?)"/){
            my $ifn = $1;
            my $idir = $dir;
            if($ifn =~ m|(.*)/(.*?\.h)|){
                $idir = "$dir/$1";
                $ifn = $2;
            }
            $res .= run($idir, $ifn);
        }else{
            $res .= $line;
        }
    }
    $flag{$n} = 1;
    return $res;
}

my $filename = shift @ARGV;

if(!defined($filename) or $filename eq ""){
    print "Err\n";
    exit(1);
}

print run(".", $filename);


