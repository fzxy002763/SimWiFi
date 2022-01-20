import java.io.*;
import java.util.*;

public class unicode2ansi{
	
	public static List<String> getFileList(File file) {  
		  
        List<String> result = new ArrayList<String>();  
  
        if (!file.isDirectory()) {  
            System.out.println(file.getAbsolutePath());  
            result.add(file.getAbsolutePath());  
        } else {  
            File[] directoryList = file.listFiles(new FileFilter() {  
                public boolean accept(File file) {  
                    if (file.isFile() && file.getName().indexOf("txt") > -1) {  
                        return true;  
                    } else {  
                        return false;  
                    }  
                }  
            });  
            for (int i = 0; i < directoryList.length; i++) {  
                result.add(directoryList[i].getPath());  
            }  
        }  
  
        return result;  
    }  

	public static void unicode2ansi(String txtFileName){
		
		try{
			
			String encoding               = "Unicode";
			String tmpLineVal;
			InputStreamReader read        = new InputStreamReader(new FileInputStream(txtFileName), encoding);
			BufferedReader bufread        = new BufferedReader(read);
			
			OutputStream write            = new FileOutputStream("temp.txt");
			OutputStreamWriter bufwrite   = new OutputStreamWriter(write);
			
			while((tmpLineVal = bufread.readLine())!=null)
			{
				bufwrite.write(tmpLineVal);
			}
			
			bufread.close();
			read.close();
			bufwrite.close();
			write.close();
			
			File file=new File(txtFileName);  
			if (file.isFile() && file.exists()) {  
		        file.delete();
		    } 
			file=new File("temp.txt");  
			if(file.isFile() && file.exists())
			{
				file.renameTo(new File(txtFileName));
			}
			
		}catch(Exception ex){
				ex.printStackTrace();
		}
	}
	
	public static void main(String args[])
	{
		File root = new File(args[0]);
		File[] files = root.listFiles();
		for(File file:files){     
			if(file.isDirectory()){
				
				String FILE_IN = file.getAbsolutePath();
				List<String> list = new ArrayList<String>();
				list = getFileList(new File(FILE_IN));
				
				for (String txtFileName : list) {
					unicode2ansi(txtFileName);
				}
				
			}
		}
	}
	
}