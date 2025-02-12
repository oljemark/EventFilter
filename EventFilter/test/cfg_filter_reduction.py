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
  input = cms.untracked.int32(100000)
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
      "/store/express/Run2023E/ExpressPhysics/FEVT/Express-v1/000/373/072/00000/f6d5eb88-219e-4dcf-bebe-a007141ce872.root",
      "/store/express/Run2023E/ExpressPhysics/FEVT/Express-v1/000/373/072/00000/f4e7a27c-bdd9-4e27-abd4-91fc2367fff0.root",
      "/store/express/Run2023E/ExpressPhysics/FEVT/Express-v1/000/373/072/00000/f4be2a53-a38c-4ef2-9184-cd398cf0cbe5.root",
#      "file:/eos/cms/store/express/Run2023E/ExpressPhysics/FEVT/Express-v1/000/372/775/00000/85a01f6c-cad8-4235-8447-50d2347fdc85.root",
)
)

process.filter = cms.EDFilter("EventFilter",
  verbosity = cms.untracked.int32(0),
  tracks = cms.untracked.InputTag('ctppsLocalTrackLiteProducer'),
  tracks2 = cms.untracked.InputTag('totemRPLocalTrackFitter'),
  l1 = cms.untracked.InputTag('scalersRawToDigi'),
  rpPatternTag = cms.InputTag('totemRPUVPatternFinder'),
  outputFileName = cms.string("output.root"),
)

process.path_filter = cms.Path(process.filter)

# output configuration
process.output = cms.OutputModule("PoolOutputModule",
  fileName = cms.untracked.string("output_skimmingSep08-r373072.root"),

  SelectEvents = cms.untracked.PSet(
    SelectEvents = cms.vstring('path_filter')
  )
)

process.path_output = cms.EndPath(process.output)

# process.path_output = cms.EndPath(process.output)
# process.schedule = cms.Schedule(process.path_filter, process.path_output)



