#!/usr/bin/perl
use strict;
use warnings;

my $range;
my $numcalls;
my $coinflip;
# print "How many elements: ";
$range = <STDIN>;
# print "How many operations: ";
$numcalls = <STDIN>;

print $range;
my $count = 0;
while ($count < $numcalls)
{
$count= $count + 1;
$coinflip = rand();
my $a = int(rand($range));
my $b = int(rand($range));
if ($coinflip < 0.3)
{
print "u ", $a, " ", $b, "\n";
}
else
{
print "f ", $a, " ", $b, "\n";
}
}
print "d\n";
