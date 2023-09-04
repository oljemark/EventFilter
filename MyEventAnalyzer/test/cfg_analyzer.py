import FWCore.ParameterSet.Config as cms

process = cms.Process("MyEventAnalyzer")

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

process.content = cms.EDAnalyzer("EventContentAnalyzer")

process.maxEvents = cms.untracked.PSet(
  input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
  dropDescendantsOfDroppedBranches = cms.untracked.bool(False),
  fileNames = cms.untracked.vstring("/store/data/Run2023C/ZeroBias11/AOD/PromptReco-v4/000/369/596/00000/513a1032-fbc6-48e0-8fc2-226677fec4cd.root",)
)

process.analyzer = cms.EDAnalyzer("MyEventAnalyzer",
  verbosity = cms.untracked.int32(0),
  tracks = cms.untracked.InputTag('ctppsLocalTrackLiteProducer'),
  tracks2 = cms.untracked.InputTag('totemRPLocalTrackFitter'),
  rpPatternTag = cms.InputTag('totemRPUVPatternFinder'),
  diagonal = cms.string("LBRT"),
  outputFileName = cms.string("output_LBRT.root"),
)

process.p = cms.Path(process.analyzer)


