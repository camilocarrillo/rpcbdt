# rpcbdt
RPC BDT studies for EMTF

```
  cmsrel CMSSW_9_2_5_patch2
  cd CMSSW_9_2_5_patch2
  git clone https://github.com/camilocarrillo/rpcbdt/ src 
  cd src
  cmsenv
  scram b 
  cmsRun rpcBDT/CPPFDigi/test/Generator_LUT1.py 
 ```
if everything goes fine the following output files are produced:
bdt_training_target.csv bdt_training_features.csv BDT_trainning_LUT_20.root

