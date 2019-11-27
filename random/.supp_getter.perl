#!/usr/bin/perl

use strict;

my $string;
while(<>){
   $string .= $_;
}

#$string =~ s/.*({.*}\n).*/$1/sg;
#print "\n\nresult:\n\n";

my @matches = ($string =~ m/({[^}]+}\n)/scg);
print join("\n", @matches);
