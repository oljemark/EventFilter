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
  input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
  dropDescendantsOfDroppedBranches = cms.untracked.bool(False),
  inputCommands = cms.untracked.vstring(
    'drop *',
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
"/store/data/Run2023C/ZeroBias11/AOD/PromptReco-v4/000/369/585/00000/dbd5bb7f-2ab6-4613-aedc-c671ba4f467d.root",
)
)

process.filter = cms.EDFilter("EventFilter",
  verbosity = cms.untracked.int32(0),
  tracks = cms.untracked.InputTag('ctppsLocalTrackLiteProducer'),
  tracks2 = cms.untracked.InputTag('totemRPLocalTrackFitter'),
  rpPatternTag = cms.InputTag('totemRPUVPatternFinder'),
  outputFileName = cms.string("output.root"),
)

process.path_filter = cms.Path(process.filter)

# output configuration
process.output = cms.OutputModule("PoolOutputModule",
  fileName = cms.untracked.string("output_skimming.root"),

  SelectEvents = cms.untracked.PSet(
    SelectEvents = cms.vstring('path_filter')
  )
)

process.path_output = cms.EndPath(process.output)

# process.path_output = cms.EndPath(process.output)
# process.schedule = cms.Schedule(process.path_filter, process.path_output)



