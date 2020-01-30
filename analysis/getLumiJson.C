void getLumiJson()
{
  
  TChain chain("ggHiNtuplizer/EventTree");
  
  
  ifstream infile("input_list.txt");
 
  string path;
  while (infile >> path){
    cout<<path<<endl;
    chain.Add(path.c_str());
  }
  
  EventTree *eventTree = new EventTree(&chain);
  eventTree->Loop();
  
}
