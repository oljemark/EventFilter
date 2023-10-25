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
  input = cms.untracked.int32(5000000)
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
#"/store/data/Run2023C/ZeroBiasNonColliding/AOD/PromptReco-v4/000/369/587/00000/e3bd3577-11b6-48ec-9ac9-e00eacabd07c.root",
#"/store/data/Run2023C/ZeroBiasNonColliding/AOD/PromptReco-v4/000/369/590/00000/afa69d5b-cf27-4b8c-9ce1-93cfadb4e477.root",
#"/store/data/Run2023C/ZeroBiasNonColliding/AOD/PromptReco-v4/000/369/591/00000/099a454b-6e38-46e0-9b19-bc6d3051023f.root",
#"/store/data/Run2023C/ZeroBiasNonColliding/AOD/PromptReco-v4/000/369/591/00000/2daf950c-8f13-416b-b299-dfb0f292e6a1.root",
#"/store/data/Run2023C/ZeroBiasNonColliding/AOD/PromptReco-v4/000/369/591/00000/41ab475c-5736-4977-818d-0b97030564d7.root",
#"/store/data/Run2023C/ZeroBiasNonColliding/AOD/PromptReco-v4/000/369/591/00000/4389b693-9df3-4a38-8890-e52c77139e69.root",
#"/store/data/Run2023C/ZeroBiasNonColliding/AOD/PromptReco-v4/000/369/591/00000/4ce27df8-24f1-435a-abd6-7cda0c561b5c.root",
#"/store/data/Run2023C/ZeroBiasNonColliding/AOD/PromptReco-v4/000/369/591/00000/5f7814e1-e26c-48a1-aa7b-12c46258a4b3.root",
#"/store/data/Run2023C/ZeroBiasNonColliding/AOD/PromptReco-v4/000/369/591/00000/62cab45a-69eb-4eb7-8879-81d156845064.root",
#"/store/data/Run2023C/ZeroBiasNonColliding/AOD/PromptReco-v4/000/369/591/00000/6f6482a9-043a-4ce0-b73d-02ce5f7f6af5.root",
#"/store/data/Run2023C/ZeroBiasNonColliding/AOD/PromptReco-v4/000/369/591/00000/783970eb-58e4-4d2b-a162-fddfb1111a21.root",
#"/store/data/Run2023C/ZeroBiasNonColliding/AOD/PromptReco-v4/000/369/591/00000/7fe612d2-8fab-452a-9104-83d9c98d6424.root",
#"/store/data/Run2023C/ZeroBiasNonColliding/AOD/PromptReco-v4/000/369/591/00000/a0641fed-0989-4f1f-8bdf-666c11797c58.root",
#"/store/data/Run2023C/ZeroBiasNonColliding/AOD/PromptReco-v4/000/369/591/00000/be5afc26-02ce-4f56-b065-f3b59a1389db.root",
#"/store/data/Run2023C/ZeroBiasNonColliding/AOD/PromptReco-v4/000/369/591/00000/d8fee924-69a9-4ea6-9bb4-8764e0b9b2e1.root",
#"/store/data/Run2023C/ZeroBiasNonColliding/AOD/PromptReco-v4/000/369/591/00000/e5655d58-276a-49d1-9821-db3852901732.root",
#"/store/data/Run2023C/ZeroBiasNonColliding/AOD/PromptReco-v4/000/369/591/00000/eec56d34-aefd-4066-9d63-63be76d3c715.root",
#"/store/data/Run2023C/ZeroBiasNonColliding/AOD/PromptReco-v4/000/369/591/00000/f623608b-72ea-48b2-a9ed-b76a6e601fad.root",
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



