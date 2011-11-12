#!/usr/bin/perl

if (@ARGV != 5){
   print "Usage: min_weight min_height max_width max_height max_threads\n";
   exit 0;
}
$minWidth = @ARGV[0];
$minHeight = @ARGV[1];
$maxWidth = @ARGV[2];
$maxHeight = @ARGV[3];
$maxCores = @ARGV[4];

system "make";
system "g++ generator.cpp -o generator";
system "mkdir testFiles";

open (RESULTS, '>results');

for($i=$minHeight ; $i<=$maxHeight ; $i=$i*10)
{
   for($j=$minWidth ; $j<=$maxWidth ; $j=$j*10)
   {
      print RESULTS "######### For height=$i and width=$j\n";
      for($nbCores = 1 ; $nbCores<=$maxCores ; $nbCores=$nbCores*2){
         print RESULTS "--- With $nbCores cores:\n";
         $output = "testFiles/test$i"."x$j";
         $generatorCommand = "./generator $i $j > $output";
         system $generatorCommand;
         $maxSubarrayCommand = "/usr/bin/time -f \"real \%e - user \%U - sys \%S\" ./run $nbCores $output 2>&1";
         $duration = `$maxSubarrayCommand`;
         print RESULTS $duration."\n";
         print("--- $nbCores threads: $i x $j done\n");
         if($nbCores==32){
            $nbCores=20;
         }
      }
   }
}

close(RESULTS);
system "rm -R testFiles";
