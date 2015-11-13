use strict;
use warnings;
use Atcoder;

use File::Slurp;
use JSON;
use Data::Printer;

die "usage: perl submit.pl <task>" if(scalar(@ARGV) < 1);

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

our $settings;
{
    my $txt = read_file("settings.json");
    $txt =~ s/\n//mg;
    $settings = decode_json($txt);
}

my $task = shift @ARGV;

my $code = sh("perl preprocess.pl $task.cpp");


my $atcoder = Atcoder->new(url => $settings->{url});
$atcoder->submit($task, $code);
