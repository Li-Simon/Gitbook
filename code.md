```
STDMETHODIMP CDataSummary::HasChanged()
{
	CComPtr<IDataset> pDataset(m_dataset);
	CComPtr<IUnknown> pSites(m_sites);

	ATLTRACE("[%d] CDataSummary::HasChanged starts, pSites=%lx, pDataset=%lx\n", GetCurrentThreadId(), pSites, pDataset);

	if (pDataset == NULL || pSites == NULL)
	{
		ATLTRACE("[%d] CDataSummary::HasChanged NULL pointer return\n", GetCurrentThreadId());
		return E_FAIL;
	}
	ATLTRACE("[%d] CDataSummary::HasChanged after null check\n", GetCurrentThreadId());
	
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		// for testing, let's always get some text into the control

				// We should be doing fancy stuff to
				// track selection and change fonts, however
				//	the RichEdit interface doesn't seem to work when
				//	we do!
	//m_ctlRichEdit.Clear();
	//m_ctlRichEdit.SetSel(0,-1);

    HCURSOR oldCursor = SetCursor (LoadCursor(NULL, IDC_WAIT));

	const int len = 2048;
	char sillyBuff[len];
	ostrstream statistics = ostrstream( sillyBuff, len);

			// show recipe name
   	//CString buffer;
	//buffer.LoadString(IDS_TEXT_SUMMARY);

	//statistics << buffer << colon << "Mystery Recipe" << newLine << newLine;

	// Display blocks of data that pertain to us
	
	// makes floats be shown in fixed format
	//statistics.setf (ios::fixed, ios::floatfield);   
			// This is a UI compromise.....instead of auto-scale
	statistics.setf (ios::scientific, ios::floatfield);   // makes floats be shown in exponential format
    statistics.setf (ios::right, ios::adjustfield);


	if (pSites != NULL && pDataset != NULL)
	{	
		CString selCaption;
		selCaption.LoadString(PMV_ID_SELECTED_DATASET);
		statistics  << tab << selCaption << newLine;
		StreamDatasetStats(statistics);
	}

	// output pn type info
	StreamPNtype(statistics);

	if (m_dsSummaries != NULL && m_selectionIndex != -1)
	{
		StreamWaferStats(statistics);
			// ^^ weird, but we have info associated with one wafer that is
			//		only available if we have a dsSummary
	}

	if (m_dsSummaries != NULL)
	{	
		if ((pSites != NULL && pDataset != NULL) || m_selectionIndex != -1)	
		{			// if there is a previous section
			statistics  << newLine << "--------------------------" << newLine;
		}
		CString selCaption;
		selCaption.LoadString(PMV_ID_TREND_STATS);
		statistics  << tab << selCaption << newLine;
		StreamDataTrendStats(statistics);
				// only show separator if we have more to show!
		statistics  << newLine << "--------------------------" << newLine;

	}

	StreamControlStats(statistics) ;

	statistics << ends;

	m_ctlRichEdit.StreamIn(statistics);

    SetCursor(oldCursor);

	ATLTRACE("[%d] CDataSummary::HasChanged ends\n", GetCurrentThreadId());
	return S_OK;
} 
```



