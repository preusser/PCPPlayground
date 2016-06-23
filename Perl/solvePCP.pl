#!/usr/bin/perl

use v5.20;
use strict;
use warnings;
use utf8;


=head1 NAME

solvePCP -- Solve a given instance of PCP

=cut


binmode STDOUT, ':utf8';


# define PCP instance
#my $instance = [['a',     'aaa'],
#                ['abaaa', 'ab'],
#                ['ab',    'b']];
my $instance = [['bba', 'b'],
                ['ba',  'baa'],
                ['ba',  'aba'],
                ['ab',  'bba']];

my $size = @$instance;

# reverse instance
my $rev_instance = [];
for (@$instance) {
  my $fst = reverse $_->[0];
  my $snd = reverse $_->[1];
  push @$rev_instance, [$fst, $snd];
}

my $max_level = 0;
eval {
  while (1) {
    $max_level += 1;
    _traverse_tree([], $size, $max_level, \&_check);
  }
};

if ($@) {
  say 'Solution: ' . join ', ', reverse @{$@};
  say 'Length of solution: ' . @{$@};
}


=head1 FUNCTIONS

=over

=item C<_traverse_tree($root, $branches, $max_level, $prune)>

This function traverses a tree recursively.

=cut

sub _traverse_tree {
  my ($root, $branches, $max_level, $prune) = @_;

  my $prune_ret = $prune->($root);

  if ($prune_ret == 1) {
    die $root;
  }

  unless ($prune_ret == -1 || @$root >= $max_level) {
    for (1 .. $branches) {
      unshift @$root, $_;
      _traverse_tree($root, $branches, $max_level, $prune);
      shift @$root;
    }
  }
}


=item C<_check($indices)>

This function returns whether a given list of indices is a solution.

It returns 1 if the list of indices is a solution, 0 if the list of indices can
possibly be extended to a solution, and -1 otherwise.

=cut

sub _check {
  my @indices = @{shift()};

  return 0 unless @indices;

  my $fst = '';
  my $snd = '';

  for (@indices) {
    $fst .= $rev_instance->[$_-1][0];
    $snd .= $rev_instance->[$_-1][1];
  }

  if ($fst eq $snd) {
    return 1;
  } elsif ($fst =~ /$snd$/ || $snd =~ /$fst$/) {
    return 0;
  } else {
    return -1;
  }
}

=back

=head1 AUTHOR

Written by Marcel Lippmann <marcel.lippmann@tu-dresden.de>.

=head1 COPYRIGHT

Copyright (c) 2015 by Marcel Lippmann.  All rights reserved.


__END__
