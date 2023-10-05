import FWCore.ParameterSet.Config as cms

process = cms.Process("EventFilter")

# minimum of logs
process.MessageLogger = cms.Service("MessageLogger",
  statistics = cms.untracked.vstring(),
  destinations = cms.untracked.vstring('cout'),
  cout = cms.untracked.PSet(
    threshold = cms.untracked.string('WARNING')
  )
)

#process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')

from Configuration.AlCa.GlobalTag import GlobalTag
# process.GlobalTag.globaltag = "101X_dataRun2_Express_v8"
process.GlobalTag.globaltag = "130X_dataRun3_Prompt_Candidate_2023_06_06_21_34_08"

process.content = cms.EDFilter("EventContentFilter")

process.maxEvents = cms.untracked.PSet(
  input = cms.untracked.int32(4800000)
)

process.source = cms.Source("PoolSource",
  dropDescendantsOfDroppedBranches = cms.untracked.bool(False),
  inputCommands = cms.untracked.vstring(
    'drop *',
	 'keep Level1TriggerScalerss_scalersRawToDigi_*_*',
	 'keep edmTriggerResults_*_*_*',
	 'keep TotemTriggerCounters_totemTriggerRawToDigi_*_*',
	 'keep TotemFEDInfos_totemRPRawToDigi_*_*',
	 'keep TotemRPDigiedmDetSetVector_totemRPRawToDigi_*_*',
	 'keep TotemVFATStatusedmDetSetVector_totemRPRawToDigi_*_*',
	 'keep TotemRPClusteredmDetSetVector_totemRPClusterProducer_*_*',
	 'keep TotemRPRecHitedmDetSetVector_totemRPRecHitProducer_*_*',
	 'keep TotemRPUVPatternedmDetSetVector_totemRPUVPatternFinder_*_*',
	 'keep TotemRPLocalTrackedmDetSetVector_totemRPLocalTrackFitter_*_*',
	 'keep TotemFEDInfos_totemT2Digis_*_*',
	 'keep TotemT2DigiedmNewDetSetVector_totemT2Digis_*_*',
	 'keep TotemVFATStatusedmDetSetVector_totemT2Digis_*_*',
	 'keep TotemT2RecHitedmNewDetSetVector_totemT2RecHits_*_*',
	 'keep TotemFEDInfos_ctppsDiamondRawToDigi_*_*',
	 'keep CTPPSDiamondDigiedmDetSetVector_ctppsDiamondRawToDigi_*_*',
	 'keep TotemVFATStatusedmDetSetVector_ctppsDiamondRawToDigi_*_*',
	 'keep CTPPSDiamondRecHitedmDetSetVector_ctppsDiamondRecHits_*_*',
	 'keep CTPPSDiamondLocalTrackedmDetSetVector_ctppsDiamondLocalTracks_*_*',
	 'keep TotemTimingLocalTrackedmDetSetVector_diamondSampicLocalTracks_*_*',
	 'keep TotemTimingDigiedmDetSetVector_totemTimingRawToDigi_*_*',
	 'keep TotemTimingRecHitedmDetSetVector_totemTimingRecHits_*_*',
	 'keep TotemTimingLocalTrackedmDetSetVector_totemTimingLocalTracks_*_*',
	 'keep CTPPSPixelDigiedmDetSetVector_ctppsPixelDigis_*_*',
	 'keep CTPPSPixelDataErroredmDetSetVector_ctppsPixelDigis_*_*',
	 'keep CTPPSPixelClusteredmDetSetVector_ctppsPixelClusters_*_*',
	 'keep CTPPSPixelRecHitedmDetSetVector_ctppsPixelRecHits_*_*',
	 'keep CTPPSPixelLocalTrackedmDetSetVector_ctppsPixelLocalTracks_*_*',
	 'keep CTPPSLocalTrackLites_ctppsLocalTrackLiteProducer_*_*',
	 'keep recoForwardProtons_ctppsProtons_*_*',
  ),
  fileNames = cms.untracked.vstring(

#"/store/data/Run2023C/ZeroBias11/AOD/PromptReco-v4/000/369/585/00000/dbd5bb7f-2ab6-4613-aedc-c671ba4f467d.root",
#"/store/data/Run2023C/ZeroBias11/AOD/PromptReco-v4/000/369/585/00000/f281dce7-1339-4658-aeac-f8b9e01608f9.root",
#"/store/data/Run2023C/ZeroBias11/AOD/PromptReco-v4/000/369/585/00000/fcfd8932-e41a-4a2c-8232-db13324fb2bc.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/585/00000/1f0b83f3-83cf-45e3-95d6-f07db38f1cbb.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/585/00000/5e295df0-d706-468d-880b-7bc24ae25b39.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/585/00000/5fae96ca-bf22-47e8-a16b-c007eef50b40.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/585/00000/b09aa2a4-2cbc-47db-b02b-c5e9284e767d.root",
#"/store/data/Run2023C/ZeroBias10/AOD/PromptReco-v4/000/369/585/00000/c105ead4-b690-4b37-ae74-5bb99cddeb52.root",
"/store/data/Run2023C/ZeroBiasNonColliding/AOD/PromptReco-v4/000/369/585/00000/0f8e5ad6-c307-4276-9b99-fd95640f83ce.root",
"/store/data/Run2023C/ZeroBiasNonColliding/AOD/PromptReco-v4/000/369/585/00000/23434de2-1d96-41d0-b5e4-0b6f0fd80622.root",
"/store/data/Run2023C/ZeroBiasNonColliding/AOD/PromptReco-v4/000/369/585/00000/5b3f2ab3-f148-4fda-ac24-a0034e1fb7f7.root",
"/store/data/Run2023C/ZeroBiasNonColliding/AOD/PromptReco-v4/000/369/585/00000/82e14c5e-2b94-49c9-9fad-1259bca1d2ae.root",
"/store/data/Run2023C/ZeroBiasNonColliding/AOD/PromptReco-v4/000/369/585/00000/c7b231d4-e396-4384-969f-e4ec735ae819.root",
"/store/data/Run2023C/ZeroBiasNonColliding/AOD/PromptReco-v4/000/369/585/00000/d21c632c-3bfb-4618-917a-4a35d85ae079.root",
"/store/data/Run2023C/ZeroBiasNonColliding/AOD/PromptReco-v4/000/369/585/00000/d7171c2e-f906-4a7f-89bd-12ef54efbf0d.root",
#"/store/data/Run2023C/ZeroBias11/AOD/PromptReco-v4/000/369/587/00000/7f81f91f-8310-46fe-ae40-fb2f7bf7536a.root",
#"/store/data/Run2023C/ZeroBias11/AOD/PromptReco-v4/000/369/590/00000/9a4aff00-b95f-46ae-8428-9e8374cea38a.root",
#"/store/data/Run2023C/ZeroBias11/AOD/PromptReco-v4/000/369/591/00000/29fc5a6a-26da-4ea0-afe8-e9446fcdd3c0.root",
#"/store/data/Run2023C/ZeroBias11/AOD/PromptReco-v4/000/369/593/00000/5b56badf-5da5-4ec1-9624-4e1144cd2db0.root",
#"/store/data/Run2023C/ZeroBias11/AOD/PromptReco-v4/000/369/594/00000/74f9570f-22d5-40c6-93e3-191d9444804a.root",
#"/store/data/Run2023C/ZeroBias11/AOD/PromptReco-v4/000/369/595/00000/0ff94c29-6990-4c3d-ab30-7f3fe0e7f8b0.root",
#"/store/data/Run2023C/ZeroBias11/AOD/PromptReco-v4/000/369/596/00000/01421d38-b975-472a-9cc0-5d0fa9855140.root",
#"/store/data/Run2023C/SpecialRandom0/AOD/PromptReco-v4/000/369/592/00000/4a1f73aa-061d-4c7d-898a-0e1c99b9bb1a.root"
#"/store/data/Run2023C/SpecialRandom0/AOD/PromptReco-v4/000/369/597/00000/6615dd5a-0e6b-4e34-8e1a-7dde70213848.root"
#"/store/data/Run2023C/SpecialRandom0/AOD/PromptReco-v4/000/369/599/00000/1552aa69-70be-46b3-8466-53b32e302b04.root"
)
)

process.filter = cms.EDFilter("EventFilter",
  verbosity = cms.untracked.int32(0),
  tracks = cms.untracked.InputTag('ctppsLocalTrackLiteProducer'),
  tracks2 = cms.untracked.InputTag('totemRPLocalTrackFitter'),
  l1 = cms.untracked.InputTag('scalersRawToDigi'),
  digisTag = cms.InputTag('totemT2Digis', 'TotemT2'),
  rpPatternTag = cms.InputTag('totemRPUVPatternFinder'),
  outputFileName = cms.string("output.root"),
)

process.path_filter = cms.Path(process.filter)

# output configuration
process.output = cms.OutputModule("PoolOutputModule",
  fileName = cms.untracked.string("output_T2skimming.root"),

  SelectEvents = cms.untracked.PSet(
    SelectEvents = cms.vstring('path_filter')
  )
)

process.path_output = cms.EndPath(process.output)

# process.path_output = cms.EndPath(process.output)
# process.schedule = cms.Schedule(process.path_filter, process.path_output)



