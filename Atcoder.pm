use strict;
use warnings;
use utf8;

package Atcoder{
    use Mouse;
    use HTTP::Cookies;
    use HTTP::Request::Common;
    use LWP;
    use Data::Printer;
    use Encode;

    has browser => (
        is => 'ro',
        isa => "LWP::UserAgent"
    );

    has url => (
        is => 'ro',
        isa => "Str",
    );

    sub BUILD{
        my $self = shift;
        my $cookie_jar = HTTP::Cookies->new(
            file => "$ENV{'HOME'}/lwp_cokkies.dat",
            autosave => 1,
        );
        my $browser = LWP::UserAgent->new;
        $browser->cookie_jar($cookie_jar);
        $self->{browser} = $browser;
    }

    sub get{
        my $self = shift;
        my $url = shift;
        my $req = GET $url;
        my $res = $self->browser()->request($req);
        if($res->is_success){
            return decode("utf8",$res->content);
        }else{
            print "err:", $res->status_line, "\n";
        }
    }

    sub login{
        my $self = shift;
        my $user = shift;
        my $passwd = shift;
        my $url = $self->url() . "/login";
        $url =~ s/http/https/;
        $url =~ s|(?<!:)//|/|g;
        print $url;
        my $req = POST $url, [ name => $user, password => $passwd];
        my $res = $self->browser()->request($req);
        if($res->is_success){
            print $res->content;
        }else{
            print "err:", $res->status_line, "\n";
        }
    }

    sub getTaskSample{
        my $self = shift;
        my $url = $self->url() . "/tasks/". shift;
        $url =~ s|(?<!:)//|/|g;
        my $data = $self->get($url);
        my @t = $data=~ m|<h3>入力例(\d+)</h3>\s*<pre.*?>\s*(.*?)\s*</pre>.*<h3>出力例\1</h3>\s*<pre.*?>\s*(.*?)\s*</pre>|sg;
        my $res = [];
        for(my $i=0;$i<scalar(@t)/3;$i++){
            my $in = $t[$i*3+1];
            $in =~ s/\r\n/\n/g;
            my $out = $t[$i*3+2];
            $out =~ s/\r\n/\n/g;
            push @$res, {
                id => $t[$i * 3],
                input => $in,
                output => $out,
            };
        }
        return $res;
    }

    sub getTasks{
        my $self = shift;
        my $url = $self->url() . "/assignments";
        $url =~ s|(?<!:)//|/|g;
        my $data = $self->get($url);
        my @t = $data =~ m|href="/tasks/(.*?)">([A-Z])</a>|g;
        my $res = [];
        for(my $i=0;$i<scalar(@t)/2;$i++){
            push @$res, {
                id => $t[$i*2+1],
                url => $self->url() ."/tasks/" . $t[$i*2+0],
                sample => $self->getTaskSample($t[$i*2+0]),
            };
        }
        return $res;
    }


    sub submit{
        my $self = shift;
        my $task = shift;
        my $code = shift;
        my $url = $self->url() . "/submit";
        $url =~ s|(?<!:)//|/|g;
        $url =~ s/http/https/;
        my %taskids;
        my $sessionid;

        {
            my $submithtml = $self->browser()->request(GET $url)->content;
            $submithtml =~ m|(<select name="task_id".*?</select>)|s;
            my $taskselect = $1;
            my @s = $taskselect =~ m|<option value="(.*?)"(?: selected)?>([A-Z])|g;
            for(my $i=0; $i < scalar(@s)/2; $i++){
                $taskids{$s[$i*2+1]} = $s[$i*2+0];
            }
            $submithtml =~ m|<input type="hidden" name="__session" value="(.*?)">|;
            $sessionid = $1;
        }
        my $taskid = $taskids{$task};
        my $data = [
            task_id => $taskid,
            "language_id_" . $taskid => 2003,
            source_code => $code,
            __session => $sessionid,
        ];
        my $req = POST $url . "?task_id=". $taskid, $data;
        my $res = $self->browser()->request($req);
        if($res->is_success){
            print $res->content;
        }else{
            print "err:", $res->status_line, "\n";
            print "redirect:", $res->request->uri();
        }
    }

    __PACKAGE__->meta->make_immutable();
}
