use strict;
use warnings;

use utf8;
use LWP::Simple;
use JSON;
use File::Slurp;
use Data::Printer;
use Atcoder;

our $settings;
{
    my $txt = read_file("settings.json");
    $txt =~ s/\n//mg;
    $settings = decode_json($txt);
}

my $atcoder = Atcoder->new(url => $settings->{url});
my $tasks = $atcoder->getTasks();

foreach my $task(@$tasks){
    foreach my $sample(@{$task->{"sample"}}){
        write_file($task->{id} . $sample->{id} . ".in", $sample->{input} . "\n");
        write_file($task->{id} . $sample->{id} . ".out", $sample->{output} . "\n");
    }
}

print "Done.";
p $tasks;
