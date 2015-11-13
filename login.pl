use strict;
use warnings;
use Atcoder;

use File::Slurp;
use JSON;

die "usage: perl login.pl <username>" if(scalar(@ARGV) < 1);

our $settings;
{
    my $txt = read_file("settings.json");
    $txt =~ s/\n//mg;
    $settings = decode_json($txt);
}

my $user = shift @ARGV;

system("stty -echo");
print "Enter your password: ";
chomp(my $passwd = <STDIN>);
print "\n";
system("stty echo");

my $atcoder = Atcoder->new(url => $settings->{url});
$atcoder->login($user, $passwd);
